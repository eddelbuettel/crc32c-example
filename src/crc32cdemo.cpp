#include <Rcpp.h>
#include <crc32cAPI.h>
#include <cstdint>

//' Demo of calling 'crc32c' functions
//'
//' The 'crc32c' website has command-line demo showing how to call the library.
//' This function \code{crc32cdemo} exposes the same functionality, but relying on R package 'crc32c'
//' to provide the object code. The two other functions provide checksum calculation examples.
//'
//' @return The function \code{crc32cdemo} is called for its side effect of printing to stdout,
//' and nothing is returned. The function \code{crc32c_raw} returns the checksum of a raw
//' input vector.
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

//' @rdname crc32cdemo
//' @param s A string
//' @examples
//' s <- "The quick brown fox"
//' crc32c_string(s)
// [[Rcpp::export]]
std::string crc32c_string(std::string s) {
  std::string val = Rcpp::as<std::string>(c_crc32c(Rcpp::wrap(s)));
  return val;
}

//' @rdname crc32cdemo
//' @param x A raw vector
//' @examples
//' r <- sin(seq(0, pi, by = 0.01))
//' rb <- writeBin(r, raw(), size = 8L)
//' crc32c_raw(rb)
// [[Rcpp::export]]
std::string crc32c_raw(Rcpp::RawVector x) {
  uint32_t val = c_crc32c_uint8(x.begin(), x.size());
  char buf[9];
  snprintf(buf, 9, "%08X", val);
  return std::string(buf);
}
