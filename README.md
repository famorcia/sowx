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

    