#include "include/flutter_doc_scanner/flutter_doc_scanner_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>
#include <memory>
#include <string>
#include <sstream>  // Include the necessary header for std::ostringstream

#include "flutter_doc_scanner_plugin.h"


namespace flutter_doc_scanner {

class FlutterDocScannerPlugin : public flutter::Plugin {
public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar) {
    auto channel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
        registrar->messenger(), "flutter_doc_scanner",
        &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<FlutterDocScannerPlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto& call, auto result) {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  void HandleMethodCall(const flutter::MethodCall<flutter::EncodableValue>& call,
                        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    if (call.method_name().compare("getPlatformVersion") == 0) {
      std::ostringstream version_stream;
      version_stream << "Windows " << GetWindowsVersion();
      result->Success(flutter::EncodableValue(version_stream.str()));
    } else {
      result->NotImplemented();
    }
  }

private:
  std::string GetWindowsVersion() {
    return "10.0";
  }
};

}  // namespace flutter_doc_scanner

void FlutterDocScannerPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_doc_scanner::FlutterDocScannerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
