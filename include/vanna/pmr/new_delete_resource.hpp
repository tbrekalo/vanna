#ifndef VANNA_NEW_DELETE_RESOURCE_HPP_
#define VANNA_NEW_DELETE_RESOURCE_HPP_

#include "vanna/pmr/memory_resource.hpp"

namespace vanna {
namespace pmr {

memory_resource* new_delete_resource() noexcept;

}
} // namespace vanna

#endif /* VANNA_NEW_DELETE_RESOURCE_HPP_ */