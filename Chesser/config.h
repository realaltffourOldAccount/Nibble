/**
 * @file config.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief
 * @version 0.2
 * @date 2019-06-01
 *
 */

/**
 * @brief Suppresses all messages.
 *
 */
//#define SUPPRESS_ALL

/**
 * @brief Unsuppresses all except for warning, info, error defines.
 *
 */
//#define UNSUPPRESS_ALL

// Check if Unsuppress_all and Suppress_all both enabled.
#if defined(UNSUPPRESS_ALL) && defined(SUPPRESS_ALL)
#error "Can't Define UNSUPPRESS_ALL and SUPPRESS_ALL at the same time."
#endif

/**
 * @brief Supresses Warnings from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_WARNING
#else
//#define SUPPRESS_WARNING  // Change this option.
#endif

/**
 * @brief Supresses Info from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_INFO
#else
//#define SUPPRESS_INFO  // Change this option.
#endif

/**
 * @brief Supresses Errors from the log.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_ERROR
#else
//#define SUPPRESS_ERROR  // Change this option.
#endif

/**
 * @brief Supresses Event Logging. Currently has no effect.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_EVENTS
#else
#define SUPPRESS_EVENTS  // Change this option.
#endif

/**
 * @brief Supresses Files Successfully read messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_FILE_SUCCESS
#else
#define SUPPRESS_FILE_SUCCESS  // Change this option.
#endif

/**
 * @brief Supresses Shader Successfully created messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_SHADER_SUCCESS
#else
#define SUPPRESS_SHADER_SUCCESS  // Change this option.
#endif

/**
 * @brief Supresses Textures Successfully created messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_TEXTURE_SUCCESS
#else
#define SUPPRESS_TEXTURE_SUCCESS  // Change this option.
#endif

/**
 * @brief Supresses Textures null warning messages.
 *
 */
#if defined(SUPPRESS_ALL)
#define SUPPRESS_TEXTURE_NULL_WARNING
#else
#define SUPPRESS_TEXTURE_NULL_WARNING  // Change this option.
#endif