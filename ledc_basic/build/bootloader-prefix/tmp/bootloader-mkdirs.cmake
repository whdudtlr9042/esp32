# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/APR/Documents/esp-idf-5.1.3/components/bootloader/subproject"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/tmp"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/src"
  "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/APR/eclipse-workspace/ledc_basic/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
