CROSS_COMPILE = 
CXX = $(CROSS_COMPILE)g++ $(CFLAGS)
CPPFLAGS = -Wall -g
AR=ar

HOST_ARCH=$(shell uname -m | sed -e 's/i.86/i686/' -e 's/^armv.*/arm/')

ifeq ($(HOST_ARCH), x86_64) 
	CPPFLAGS += -m64
	SDK_LIB_SUBDIR=m64x86
else ifeq ($(HOST_ARCH), i686) 
	CPPFLAGS += -m32
	SDK_LIB_SUBDIR=m32x86
else
endif

TARGET = test

INCLUDES = -I./include
LINKLIBS = -L./depends/$(SDK_LIB_SUBDIR) -lMVSDK -lrt -lpthread
LINKLIBS += -L../../../lib -lMVSDK
LINKLIBS += /home/sylar/catkin_ws/src/dahua_cam/depends/m64x86/libImageConvert.so
LINKLIBS +=  -I/usr/include/opencv -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_line_descriptor -lopencv_optflow -lopencv_video -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_rgbd -lopencv_viz -lopencv_surface_matching -lopencv_text -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

$(TARGET):$(OBJECTS)
	$(CXX) $(INCLUDES) $(CPPFLAGS) $(OBJECTS) $(LINKLIBS) -o $(TARGET)
	rm -f $(OBJECTS)
	
.cpp.o:
	$(CXX) $(INCLUDES) -c $(CPPFLAGS) $< -o $@
	
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)

	
