#include "include/flutter_doc_scanner/flutter_doc_scanner_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>
#include "flutter_doc_scanner_plugin.h"

// This function bridges the C API to the C++ implementation of the plugin.
void FlutterDocScannerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_doc_scanner::FlutterDocScannerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
