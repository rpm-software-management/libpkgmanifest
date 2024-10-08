#include "impl/libpkgmanifest/yaml/iyamlnodeinternal.hpp"

using namespace libpkgmanifest::internal;

namespace {

// note: to be only used with YamlNodeInternalStub instances inside!
class YamlNodeInternalStub : public IYamlNodeInternal {
public:
    YamlNodeInternalStub() = default;
    YamlNodeInternalStub(const YamlNodeInternalStub & other) 
        : string_value(other.string_value), 
          int_value(other.int_value), 
          uint_value(other.uint_value), 
          uint64_value(other.uint64_value) {
        for (const auto & [key, node] : other.nodes_map) {
            nodes_map[key] = std::make_unique<YamlNodeInternalStub>(*dynamic_cast<YamlNodeInternalStub*>(node.get()));
        }

        for (const auto & node : other.nodes_list) {
            nodes_list.push_back(std::make_unique<YamlNodeInternalStub>(*dynamic_cast<YamlNodeInternalStub*>(node.get())));
        }
    }

    bool has(const std::string & key) const override {
        return nodes_map.find(key) != nodes_map.end();
    }

    std::unique_ptr<IYamlNode> get(const std::string & key) const override {
        return std::unique_ptr<IYamlNode>(new YamlNodeInternalStub(*dynamic_cast<YamlNodeInternalStub*>(nodes_map.at(key).get())));
    }

    std::string as_string() const override {
        return string_value;
    }

    int as_int() const override {
        return int_value;
    }

    unsigned as_uint() const override {
        return uint_value;
    }

    uint64_t as_uint64() const override {
        return uint64_value;
    }

    std::vector<std::unique_ptr<IYamlNode>> as_list() const override {
        std::vector<std::unique_ptr<IYamlNode>> cloned_list;

        for (const auto & node : nodes_list) {
            cloned_list.push_back(std::make_unique<YamlNodeInternalStub>(*dynamic_cast<YamlNodeInternalStub*>(node.get())));
        }
        
        return cloned_list;
    }

    std::map<std::string, std::unique_ptr<IYamlNode>> as_map() const override {
        std::map<std::string, std::unique_ptr<IYamlNode>> cloned_map;

        for (const auto & [key, node] : nodes_map) {
            cloned_map[key] = std::make_unique<YamlNodeInternalStub>(*dynamic_cast<YamlNodeInternalStub*>(node.get()));
        }

        return cloned_map;
    }

    void set(const std::string & value) override {
        string_value = value;
    }

    void set(int value) override {
        int_value = value;
    }

    void set(unsigned value) override {
        uint_value = value;
    }

    void set(uint64_t value) override {
        uint64_value = value;
    }

    void add(std::unique_ptr<IYamlNode> value) override {
        nodes_list.push_back(std::move(value));
    }

    void insert(const std::string & key, std::unique_ptr<IYamlNode> value) override {
        nodes_map[key] = std::move(value);
    }

private:
    std::string string_value;
    int int_value;
    unsigned uint_value;
    uint64_t uint64_value;

    std::map<std::string, std::unique_ptr<IYamlNode>> nodes_map;
    std::vector<std::unique_ptr<IYamlNode>> nodes_list;
};

}
