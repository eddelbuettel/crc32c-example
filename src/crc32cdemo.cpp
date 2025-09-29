#include <Rcpp.h>
#include <crc32cAPI.h>
#include <cstdint>

//' Demo of calling 'crc32c' functions
//'
//' The 'crc32c' website has command-line demo showing how to call the library.
//' This function exposes the same functionality, but relying on R package 'crc32c'
//' to provide the object code.
//'
//' @return The function is called for its side effect of printing to stdout,
//' nothing is returned
// [[Rcpp::export]]
void crc32cdemo() {

    const std::uint8_t buffer[] = {0, 0, 0, 0};
    std::uint32_t result;

    // Process a raw buffer.
    result = c_crc32c_uint8(buffer, 4);
    Rcpp::Rcout << "Result of buffer is " << result << std::endl;

    // Process a std::string.
    std::string string;
    string.resize(4);
    auto res = c_crc32c(Rcpp::wrap(string));
    Rcpp::Rcout << "Result of string is " << res << std::endl;

}
