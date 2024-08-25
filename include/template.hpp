#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <optional>

namespace tmpl {
  std::optional<std::ifstream> renderTemplate(std::string& path) {
    std::ifstream tmpl(path, std::ios_base::binary);
    if (tmpl.fail()) {
      std::cerr << "Unable to render template with path: " << path << "\n";
      return std::nullopt;
    }
    return std::optional<std::ifstream>(tmpl);
  }
  
}

#endif