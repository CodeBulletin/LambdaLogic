//
// Created by bhavesh on 4/3/23.
//
#pragma once

#include <string>
#include <utility>

class Object {
public:
    Object(): m_id(id_counter++) {}
    Object(const std::string& type): m_id(id_counter++), m_type(type) {}
    Object(int id, const std::string& type): m_id(id), m_type(type) {}
    Object(const Object& other): m_id(other.m_id), m_type(other.m_type) {}
    Object(Object&& other) noexcept: m_id(other.m_id), m_type(std::move(other.m_type)) {}
    ~Object() = default;

    [[nodiscard]] int getId() const {
        return this->m_id;
    }

    [[nodiscard]] std::string getType() const {
        return this->m_type;
    }

private:
    const int m_id = 0;
    const std::string m_type = "Object";
    static int id_counter;
};