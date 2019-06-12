/**
 * @file FileManager.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definition of the file manager.
 * @version 0.1
 * @date 2019-06-02
 *
 */

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "common.h"
#include "error_macros.h"
#include "macros.h"
#if defined(__ANDROID__)
#include "vendor/file_compat.h"
#endif

namespace GEngine {
namespace Files {
/**
 * @brief The definition of the file manager.
 *
 */
class FileManager {
   public:
	/**
	 * @brief Reads a file.
	 *
	 * @param file			The file path.
	 * @return std::string	The file data.
	 */
	static std::string LoadFile(std::string file);
	/**
	 * @brief Write to a file.
	 *
	 * @param file			The file path.
	 * @param data			The file data.
	 */
	static void WriteFile(std::string file, std::string data);
	/**
	 * @brief Returns a file size.
	 *
	 * @param filename					The file name.
	 * @return std::ifstream::pos_type	The file size.
	 */
	static long FileSize(std::string file);

   private:
	/* data */
};

}  // namespace Files
}  // namespace GEngine

#endif