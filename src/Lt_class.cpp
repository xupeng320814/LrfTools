#include "Lt_class.h"

uint64_t Lt_class::instanceCount_ = 0;

Lt_class::Lt_class() 
        : id_(0)
        , name_("default")
{
        std::cout << "Lt_class()" << std::endl;
        ++instanceCount_;
}

Lt_class::Lt_class(uint64_t id, const std::string& name)
        : id_(id)
        , name_(name) 
{
        std::cout << "Lt_class(uint64_t id, const std::string& name)" << std::endl;
        ++instanceCount_;
}

Lt_class::Lt_class(const Lt_class& other)
        : id_(other.id_)
        , name_(other.name_) 
{
        std::cout << "Lt_class(const Lt_class& other)" << std::endl;
        ++instanceCount_;
}

Lt_class::Lt_class(Lt_class&& other) noexcept
        : id_(other.id_)
        , name_(std::move(other.name_))
{
        std::cout << "Lt_class(Lt_class&& other)" << std::endl;
        ++instanceCount_;
}

Lt_class& Lt_class::operator=(const Lt_class& other)
{
        std::cout << "operator=(const Lt_class& other)" << std::endl;
        if (this != &other)
        {
                id_ = other.id_;
                name_ = other.name_;
        }
        return *this;
}

Lt_class& Lt_class::operator=(Lt_class&& other) noexcept
{
        std::cout << "operator=(Lt_class&& other)" << std::endl;
        if (this != &other)
        {
                id_ = other.id_;
                name_ = std::move(other.name_);
        }
        return *this;
}

Lt_class::~Lt_class() {
        std::cout << "~Lt_class()" << std::endl;
        --instanceCount_;
}

void Lt_class::Print() const 
{
        std::cout << "Lt_class { id: " << id_ << ", name: " << name_ << " }" << std::endl;
}

uint64_t Lt_class::GetId() const 
{
        return id_;
}

void Lt_class::SetId(uint64_t id) 
{ 
        id_ = id;
}

uint64_t Lt_class::GetInstanceCount() 
{
        return instanceCount_;
}

std::ostream& operator<<(std::ostream& os, const Lt_class& obj)
{
        os << "Lt_class {id: " << obj.id_ << ", name: " << obj.name_ << " }";
        return os;
}