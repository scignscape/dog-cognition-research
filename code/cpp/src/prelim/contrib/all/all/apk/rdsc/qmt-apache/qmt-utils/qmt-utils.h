

#ifndef QMT_UTILS__H
#define QMT_UTILS__H

#ifdef __cplusplus
extern "C" {
#endif

void log_comments(const char* file, const char* msg);

void log_comments_with_value(const char* file, const char* msg, int i);

void log_comments_kv(const char* file, const char* k, const char* v);

void log_pointer_raw_value(const char* file, const char* name, void* v);


int get_response_array(void* url, char*** response, const char* log_file);

//void* get_qmt_response(void* url);


//int get_canned_response(void* url, char** response);
//int get_external_response(void* url, char*** response);

int _parse_url_via_start(const char* log_file, const char* url, const char* required_start,
  int* positive_response, int suggested_negative_response,
  void** details);

#ifdef __cplusplus
 } // extern "C"
#endif



#endif // QMT_UTILS__H
