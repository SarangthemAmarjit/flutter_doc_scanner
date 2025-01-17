#include "flutter_doc_scanner_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_doc_scanner {

// Static method to register the plugin with the registrar.
void FlutterDocScannerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows* registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_doc_scanner",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterDocScannerPlugin>();

  // Set up a method call handler for the channel.
  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto& call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

// Constructor
FlutterDocScannerPlugin::FlutterDocScannerPlugin() {}

// Destructor
FlutterDocScannerPlugin::~FlutterDocScannerPlugin() {}

// Handle method calls from the Dart side.
void FlutterDocScannerPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  // Handle the "getPlatformVersion" method.
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";

    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    } else {
      version_stream << "Unknown Version";
    }

    result->Success(flutter::EncodableValue(version_stream.str()));

  // Add support for additional methods here.
  } else if (method_call.method_name().compare("startScan") == 0) {
    // Example: Implement logic for starting a scan operation.
    result->Success(flutter::EncodableValue("Scanning started"));

  } else if (method_call.method_name().compare("getScanResult") == 0) {
    // Example: Implement logic for retrieving scan results.
    result->Success(flutter::EncodableValue("Scan result data"));

  } else {
    // If the method is not implemented, respond with "NotImplemented".
    result->NotImplemented();
  }
}

}  // namespace flutter_doc_scanner
