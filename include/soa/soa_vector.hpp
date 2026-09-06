#pragma once

#include <cstddef>
#include <meta>
#include <tuple>
#include <utility>
#include <vector>

namespace soa {

template<class T>
consteval auto storage_type_of() {
    std::vector<std::meta::info> columns;
    auto ctx = std::meta::access_context::current();

    for (auto member : std::meta::nonstatic_data_members_of(^^T, ctx)) {
        columns.push_back(
            std::meta::substitute(
                ^^std::vector,
                {std::meta::type_of(member)}
            )
        );
    }

    return std::meta::substitute(^^std::tuple, columns);
}

template<class T>
struct ref_builder {
    struct type;

    consteval {
        std::vector<std::meta::info> fields;
        auto ctx = std::meta::access_context::current();

        for (auto member : std::meta::nonstatic_data_members_of(^^T, ctx)) {
            fields.push_back(
                std::meta::data_member_spec(
                    std::meta::add_lvalue_reference(
                        std::meta::type_of(member)
                    ),
                    {.name = std::meta::identifier_of(member)}
                )
            );
        }

        std::meta::define_aggregate(^^type, fields);
    }
};

template<class T>
class vector {
    using storage_type = [:storage_type_of<T>():];

public:
    using value_type = T;
    using reference = typename ref_builder<T>::type;

    void reserve(std::size_t n) {
        std::apply(
            [n](auto&... columns) {
                (columns.reserve(n), ...);
            },
            data_
        );
    }

    void push_back(const T& value) {
        push_back(value, std::make_index_sequence<count()>{});
        ++size_;
    }

    reference operator[](std::size_t i) {
        return at(i, std::make_index_sequence<count()>{});
    }

    std::size_t size() const noexcept {
        return size_;
    }

private:
    static consteval std::size_t count() {
        return std::meta::nonstatic_data_members_of(
            ^^T,
            std::meta::access_context::current()
        ).size();
    }

    template<std::size_t I>
    static consteval std::meta::info member() {
        return std::meta::nonstatic_data_members_of(
            ^^T,
            std::meta::access_context::current()
        )[I];
    }

    template<std::size_t... I>
    void push_back(const T& value, std::index_sequence<I...>) {
        (
            std::get<I>(data_).push_back(
                value.[:member<I>():]
            ),
            ...
        );
    }

    template<std::size_t... I>
    reference at(std::size_t i, std::index_sequence<I...>) {
        return reference{
            std::get<I>(data_)[i]...
        };
    }

    storage_type data_;
    std::size_t size_ = 0;
};

}