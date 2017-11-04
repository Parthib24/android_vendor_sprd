# Copyright (C) 2012 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

COMMON_PROPRIETARY_FILES := \
	bin/at_distributor \
	bin/npsmobex \
	bin/refnotify \
	bin/engpc \
	bin/gpsd \
	bin/gps.cer \
	bin/rild_sprd \
	bin/modemd \
	bin/nvitemd \
	bin/phoneserver \
	bin/modem_control \
	bin/ext_data.sh \
	bin/ext_kill.sh \
	bin/ext_symlink.sh \
	bin/prepare_param.sh \
	bin/sswap \
	lib/libAl_Awb.so \
	lib/libAl_Awb_Sp.so \
	lib/soundfx/libaudiosa_sec.so \
	lib/soundfx/libaudioeffectoffload.so \
	lib/libisp.so \
	lib/libynoise.so \
	lib/libspaf.so \
	lib/liblsc.so \
	lib/libyasalgo.so \
	lib/libril.so \
	lib/libreference-ril_sp.so \
	lib/libsecril-client.so \
	lib/libsecnativefeature.so \
	lib/lib_SoundAlive_play_ver125e.so \
	lib/liblcsagent.so \
	lib/libboost.so \
	lib/libfactoryutil.so \
	lib/libatchannel.so \
	lib/libatparser.so \
	lib/libomx_avcdec_hw_sprd.so \
	lib/libomx_avcenc_hw_sprd.so \
	lib/libomx_vpxdec_hw_sprd.so \
	lib/libomx_m4vh263dec_hw_sprd.so \
	lib/libomx_m4vh263enc_hw_sprd.so \
	lib/libomission_avoidance.so \
	vendor/firmware/BCM4343A0_001.001.034.0056.0197_M_ORC_Core3.hcd \
	vendor/firmware/fw_bcmdhd.bin \
	vendor/firmware/fw_bcmdhd_apsta.bin \
	vendor/firmware/vbc_eq \
	vendor/lib/mediadrm/libdrmclearkeyplugin.so \
	vendor/lib/libavcodec.so \
	vendor/lib/libavformat.so \
	vendor/lib/libavutil.so \
	vendor/lib/libbt-vendor.so \
	vendor/lib/libffmpeg_extractor.so \
	vendor/lib/libffmpeg_omx.so \
	vendor/lib/libffmpeg_utils.so \
	vendor/lib/libswresample.so \
	vendor/lib/libswscale.so

PRODUCT_COPY_FILES += \
    $(foreach f,$(COMMON_PROPRIETARY_FILES),vendor/sprd/proprietaries/scx31c/system/$(f):system/$(f))
