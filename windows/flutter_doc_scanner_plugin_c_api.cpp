#include "include/flutter_doc_scanner/flutter_doc_scanner_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>
#include <memory>
#include <string>
#include <sstream>  // Include the necessary header for std::ostringstream

#include "flutter_doc_scanner_plugin.h"

// Namespace to encapsulate the plugin logic
namespace flutter_doc_scanner{

class FlutterDocScannerPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar) {
    auto channel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
        registrar->messenger(), "flutter_doc_scanner",
        &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<FlutterDocScannerPlugin>();

    // Register method call handlers for the plugin
    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto& call, auto result) {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  // Method to handle method calls from Flutter
  void HandleMethodCall(const flutter::MethodCall<flutter::EncodableValue>& call,
                        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    if (call.method_name().compare("getPlatformVersion") == 0) {
      std::ostringstream version_stream;
      version_stream << "Windows " << GetWindowsVersion();  // Concatenates the platform version
      result->Success(flutter::EncodableValue(version_stream.str()));
    } else {
      result->NotImplemented();
    }
  }

 private:
  // Example utility method to get the Windows version
  std::string GetWindowsVersion() {
    // This is a simple placeholder; replace it with actual logic for fetching the OS version.
    return "10.0";
  }
};
void FlutterDocScannerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_doc_scanner::FlutterDocScannerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
}  // namespace






