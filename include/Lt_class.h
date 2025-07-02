#pragma once
#include <string>
#include <iostream>

class Lt_class
{
public:
	Lt_class();
	Lt_class(uint64_t id, const std::string& name);
	Lt_class(const Lt_class& other);
	Lt_class(Lt_class&& other) noexcept;
	Lt_class& operator=(const Lt_class& other);
	Lt_class& operator=(Lt_class&& other) noexcept;
	~Lt_class();

public:
	void Print() const;
	uint64_t GetId() const;
	void SetId(uint64_t id);
	static uint64_t GetInstanceCount();
	friend std::ostream& operator<<(std::ostream& os, const Lt_class& obj);

private:
	uint64_t id_;
	std::string name_;
	static uint64_t instanceCount_;
};