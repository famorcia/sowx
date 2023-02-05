# SoWx
Coin GUI binding for wxWidgets

## Platform supported

Thanks to the powerful porting support provided by wxWidgets SoWx has been successfully compile on:

 - Linux
   - GTK binding (preferred)
   - X11 binding
   - Qt binding
 - Windows
 - Mac OS (coming soon)

## Linux compile

Required libs are:

 - wxWidgets (version >= 3.2)
 - Coin (version >= 4.0)
 - boost (version >= 1.48 only for test )

For other details please refer to [INSTALL](./INSTALL).

## cpack 

cpack can generate configuration for predefined platform.
cpack needs to be enabled in cmake setting SOWX_USE_CPACK to ON

Packages for platform can be generated using specific platforms 
(e.g. cpack --config cmake-build-debug/cpack.d/centos.cmake).


## Windows address sanitizer
Add 
	"addressSanitizerEnabled": true,
in CMakeSettings.json

## Known limitations

    