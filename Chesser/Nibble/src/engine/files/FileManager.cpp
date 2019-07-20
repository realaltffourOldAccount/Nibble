#include "FileManager.h"

namespace GEngine {
    namespace Files {
        std::string FileManager::LoadFile(std::string file) {
#if !defined(__ANDROID__)
            std::ifstream filestream;
            filestream.open(file);
            if (filestream.is_open() == false) {
                THROW_ERROR("Error Could not open file: " + file + ".",
                        Log::GenLogID(__LINE__, __FILE__, "FileManager", __func__));
            } else {
#if !defined(SUPPRESS_FILE_SUCCESS)
                Log::info("Succussfully read file: " + file + ". ",
                        Log::GenLogID(__LINE__, __FILE__, "FileManager", __func__));
#endif
            }

            std::stringstream ss;
            ss << filestream.rdbuf();
            filestream.close();
            return ss.str();
#else
            ANativeActivity* activity = glfmAndroidGetActivity();
            AAssetManager* manager = NULL;
            if (activity) {
                manager = activity->assetManager;
            }
            AAsset* fileasset =
                AAssetManager_open(manager, file.c_str(), AASSET_MODE_BUFFER);
            off_t fileassetSize = AAsset_getLength(fileasset);

            char* fileassetData = new char[fileassetSize];
            int redres = AAsset_read(fileasset, fileassetData, (size_t)fileassetSize);
            if (redres != 0 && redres == fileassetSize) {
#if !defined(SUPPRESS_FILE_SUCCESS)
                Log::info("Succussfully read file: " + file + ". ",
                        Log::GenLogID(__LINE__, __FILE__, "FileManager", __func__));
#endif
            } else {
                Log::error("Failed to read file: " + file + ". ",
                        Log::GenLogID(__LINE__, __FILE__, "FileManager", __func__));
            }
            AAsset_close(fileasset);
            fileassetData += '\0';
            return std::string(fileassetData);
#endif
        }
        void WriteFile(std::string file, std::string data) {
            // TODO: Check working on android.
            std::ofstream filestream;
            filestream.open(file);
            if (filestream.is_open() == false) {
                THROW_ERROR(
                        "Error Could not open file: " + file + ".",
                        Log::GenLogID(__LINE__, __FILE__, "FileManager", "WriteFile()"));
            }

            filestream << data;
        }

        long FileSize(std::string file) {
            std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
            auto size = in.tellg();
            in.close();
            return size;
        }
    }  // namespace Files
}  // namespace GEngine
