// SPDX-License-Identifier: zlib-acknowledgement
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
// exuberant ctags for utilising projects (gives definitions)
// 1. external libraries 
// TODO(Ryan): Only working for struct definitions and not functions?
// Documentation is sparse, should I build from source so I can inspect sources for documentation?
// How to read linux-docs
// 2. system calls
// 3. c standard library

// cscope for modifying (gives callers)

// libdrm wraps DRM ioctls?
#include <xf86drm.h>
#include <xf86drmMode.h>

inline void DEBUGGER_BREAK(void) { return; }
void break_and_log_errno(char const *msg)
{
  char errno_msg[256] = {0};
  // TODO(Ryan): With better gnu++20 support, use std::format
  sprintf(errno_msg, "%s %m", msg);
  // IMPORTANT(Ryan): Instruct debugger to break at this function call
  // and then simply step out to inspect errno_msg in expressions window
  DEBUGGER_BREAK();
}

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;
typedef int32_t s32;

int
main(int argc, char* argv[])
{ // NOTE(Ryan): For every device the linux kernel detects, it will export obtained information about the device
  // via sysfs (so, a file is present in /sys/dev/char or sys/dev/block depending on how the driver sends data)
  // It will also send a uevent to the udevd systemd service/daemon whose subsequent action can be configured.
  // In most cases will put in /dev.
  
  // TODO(Ryan): Investigate using libudev to avoid hard-coding.
  int drm_fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);
  if (drm_fd == -1) {
    break_and_log_errno("Unable to open DRM device");
  }

  // TODO(Ryan): Even worth considering as every driver should support?
  u64 has_dumb = 0;
  if (drmGetCap(drm_fd, DRM_CAP_DUMB_BUFFER, &has_dumb) < 0 || !has_dumb) {
    break_and_log_errno("DRM driver does not support dumb buffers");
  }

  drmModeRes *drm_info = drmModeGetResources(drm_fd);
  if (drm_info == NULL) {
    break_and_log_errno("Unable to get resources for DRM card");
  }

  // TODO(Ryan): Support multiple monitors, i.e. multiple connectors
  drmModeConnector *drm_connector = NULL;
  for (u32 connector_i = 0; connector_i < drm_info->count_connectors; ++connector_i) {
    drmModeConnector *drm_test_connector = \
      drmModeGetConnector(drm_fd, drm_info->connectors[connector_i]);

    if (drm_test_connector == NULL) {
      break_and_log_errno("Cannot retrieve DRM connector");
      continue;
    }

    if (drm_test_connector->connection == DRM_MODE_CONNECTED && 
          drm_test_connector->count_modes != 0) {
      drm_connector = drm_test_connector;
      break;
    } else {
      drmModeFreeConnector(drm_test_connector);
    }
  }
  if (drm_connector == NULL) {
    break_and_log_errno("Unable to get a connected connector");
  }

  s32 crtc = -1;
  for (u32 encoder_i = 0; encoder_i < drm_connector->count_encoders; ++encoder_i) {
    drmModeEncoder *drm_encoder = \
      drmModeGetEncoder(drm_fd, drm_connector->encoders[encoder_i]);

    if (drm_encoder == NULL) {
      break_and_log_errno("Cannot retrieve encoder");
      continue;
    }

    for (u32 crtc_i = 0; crtc_i < drm_info->count_crtcs; ++crtc_i) {
      // check if crtc works with encoder
      if ((drm_encoder->possible_crtcs & (1 << crtc_i)) == 0) {
        continue;
      } else {
        crtc = drm_info->crtcs[crtc_i];
        drmModeFreeEncoder(drm_encoder);
        break;
      }
    }
    drmModeFreeEncoder(drm_encoder);
  }
  if (crtc == -1) {
    break_and_log_errno("Unable to get encoder with crtc");
  }

  // fbs and handles???
  // saving crtc to reconfigure at end

  // TODO(Ryan): Use libgdm to create buffer for opengl/mesa context. 
  struct drm_mode_create_dumb drm_dumb_buf_info = {};
  drm_dumb_buf_info.width = drm_connector->modes[0].hdisplay;
  drm_dumb_buf_info.height = drm_connector->modes[0].vdisplay;
  drm_dumb_buf_info.bpp = 32;
  int drm_dumb_buf_info_ret = \
    drmIoctl(drm_fd, DRM_IOCTL_MODE_CREATE_DUMB, &drm_dumb_buf_info);

  if (drm_dumb_buf_info_ret < 0) {
    break_and_log_errno("Cannot create dumb buffer");
  }
  drm_dumb_buf_info_ret = drmModeAddFB(drm_fd, 
                       drm_dumb_buf_info.width, drm_dumb_buf_info.height, 
                       24, 32, 
                       drm_dumb_buf_info.pitch, 
                       drm_dumb_buf_info.handle, 
                       drm_info->fbs
                     );
  if (drm_dumb_buf_info_ret != 0) {
    break_and_log_errno("Cannot create dumb buffer");
  }

  u32 size = drm_dumb_buf_info.size;
  struct drm_mode_map_dumb mreq = {};
  mreq.handle = drm_dumb_buf_info.handle;
  int drm_map_dumb_buf_ret = drmIoctl(drm_fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
  if (drm_map_dumb_buf_ret != 0) {
    break_and_log_errno("Cannot map dumb buffer");
  }

  u32 buffer_width = drm_dumb_buf_info.width;
  u32 buffer_height = drm_dumb_buf_info.height;

  void *buffer = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, drm_fd, mreq.offset); 
  if (buffer == MAP_FAILED) {
    break_and_log_errno("Cannot mmap dumb buffer");
  }
  memset(buffer, 0, size);

  /*
  struct drm_mode_destroy_dumb dreq = {0};
  dreq.handle = handle;
  drmIoctl(drm_fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);
  */
  
  // need to be DRM master to perform modesetting. currently only X is.
  // perform actual modesetting
  drmModeCrtc *ctrc_obj = drmModeGetCrtc(drm_fd, crtc);
  u32 should_be_connector = 0;
  int ret = drmModeSetCrtc(drm_fd, crtc, mreq.handle, 0, 0, &should_be_connector, 1, &drm_connector->modes[0]);
  if (ret != 0) {
    break_and_log_errno("Cannot set crtc for connector");
  }

  bool want_to_run = true; 
  while (want_to_run) {
    for (u32 y = 0; y < buffer_height; ++y) {
      for (u32 x = 0; x < buffer_width; ++x) {
        u8 alpha = 0;
        u8 red = 253;
        u8 green = 246;
        u8 blue = 227;

        *(u32 *)&buffer[x + y * buffer_width] = alpha << 24 | red << 16 | green << 8 | blue;
      }
    }
  }

  cleanup();
  close(drm_fd);

  return 0;
}


