#pragma once

#include <c10/core/Backend.h>
#include <c10/core/ScalarType.h>
#include <c10/core/Layout.h>

namespace at {

class TypeProperties {
 public:
  TypeProperties(Backend backend=Backend::Undefined, ScalarType scalar_type=ScalarType::Undefined)
    : backend_(backend), scalar_type_(scalar_type) {}

  Backend backend() const {
    return backend_;
  }

  bool is_sparse() const {
    return layout_from_backend(backend()) == kSparse;
  }

  DeviceType device_type() const {
    return backendToDeviceType(backend_);
  }

  bool is_cuda() const {
    return backendToDeviceType(backend_) == kCUDA;
  }

  ScalarType scalar_type() const {
    return scalar_type_;
  }

  caffe2::TypeMeta typeMeta() const {
    return scalarTypeToTypeMeta(scalar_type_);
  }

  bool is_defined() const {
    return backend_ != Backend::Undefined && scalar_type_ != ScalarType::Undefined;
  }

  TypeProperties& operator=(const TypeProperties& other) {
    if (this != &other) {
      backend_ = other.backend();
      scalar_type_ = other.scalar_type();
    }
    return *this;
  }

  bool operator==(const TypeProperties& other) const {
    return backend_ == other.backend() && scalar_type_ == other.scalar_type();
  }

  bool operator!=(const TypeProperties& other) const {
    return !(*this == other);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << at::toString(backend()) << at::toString(scalar_type()) << "Type";
    return ss.str();
  }

 private:
  Backend backend_;
  ScalarType scalar_type_;
};

}  // namespace at
