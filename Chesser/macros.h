#define THROW_ERROR(ptr, msg) \
    Log::error(msg);          \
    ptr->error = true
