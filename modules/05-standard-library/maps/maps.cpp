
// Demo the use of map and unordered_map data structures.
// See here: https://youtu.be/KiB0vRi2wlc

// See here for more details on defining a custom hash:
// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

// ReSharper disable CppUseDesignatedInitializers
#include <cstdint>

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <map> // ordered, typically a red-black tree
using std::map;

#include <unordered_map> // hash table, typically faster
using std::unordered_map;

namespace {

  struct CityRecord {

    string name;
    uint64_t population = 0;
    double latitude = 0.0, longitude = 0.0;

    // Need operator== (plus a hash function, see below) to use CityRecord as a key in an unordered_map.
    bool operator==(const CityRecord& that) const {
      return (name == that.name);
      //return
      //   (name == that.name) &&
      //   (population == that.population) &&
      //   (latitude == that.latitude) &&
      //   (longitude == that.longitude); // better!
    }

    // Need operator< to use CityRecord as a key in a (sorted) map.
    bool operator<(const CityRecord& that) const { return population < that.population; }

    friend ostream& operator<<(ostream& os, const CityRecord& cr);
  };

  ostream& operator<<(ostream& os, const CityRecord& cr) {
    os << "Name: " << cr.name << ", Population: " << cr.population <<
      ", Latitude: " << cr.latitude << ", Longitude: " << cr.longitude;
    return os;
  }

} // namespace

// Using an unordered_map requires a hash function over the map keys. If you are tempted to hash directly off of
// CityRecord, first consider hashing from a CityRecord* pointer, which is just a uint64_t. Otherwise, specialize
// the hash template like this.
template<>
struct std::hash<CityRecord> {
  size_t operator()(const CityRecord& key) const noexcept {
    return hash<string>()(key.name); // should be a unique function
  }
};

int main() {

  map<string, CityRecord> city_map;
  city_map["Melbourne"] = CityRecord{"Melbourne", 500000, 2.4, 9.4};
  city_map["LOL-Town"] = CityRecord{"LOL-Town", 500000, 2.4, 9.4};
  city_map["Berlin"] = CityRecord{"Berlin", 500000, 2.4, 9.4};
  city_map["Paris"] = CityRecord{"Paris", 500000, 2.4, 9.4};
  city_map["London"] = CityRecord{"London", 500000, 2.4, 9.4};

  cout << "Retrieve a value with the index operator.\n";
  const CityRecord& berlin_data = city_map["Berlin"];
  cout << berlin_data << endl;

  // Calling the index operator[] (even on the right-hand size), with a key not 
  // in the map inserts the missing key and returns a reference to the value.
  cout << "\nCalling the index operator with a missing key returns a default value instance.\n";
  CityRecord& missing_city = city_map["Tokyo"];
  cout << missing_city << endl; // 

  // Value updates via the reference are reflected in the map. This avoids the 
  // need to create the CityRecord on the stack and then copy it into the map.
  cout << "\nUse the reference returned for a missing key to update data in-place..\n";
  missing_city.name = "Tokyo";
  missing_city.population = 555555;
  missing_city.latitude = 12.34;
  missing_city.longitude = 123.45;
  cout << city_map["Tokyo"] << endl;

  cout << "\nUse at() to retrieve the data without inserting missing values.\n";
  // cout << city_map["Hong Kong"] << endl;  // *adds* a record for Hong Kong, probably not what you wanted
  cout << city_map.at("Berlin") << endl;
  if(city_map.contains("Hong Kong")) {
    const CityRecord& hong_kong_data = city_map.at("Hong Kong");
    cout << hong_kong_data << endl;
  } else {
    cout << "Hong Kong not found.\n";
  }
  
  cout << "\nPrint all entries using C++14 (results for a map are sorted by key).\n";
  // ReSharper disable once CppUseStructuredBinding
  for(pair<const string, CityRecord>& /*auto&*/ kv: city_map) {
    const string& name = kv.first;
    CityRecord& city = kv.second;
    cout << "Key: " << name << ", Value: " << city << endl;
  }

  cout << "\nPrint all entries using C++17 structured bindings notation.\n";
  for(auto& [name, city] : city_map) {
    cout << "Key: " << name << ", Value: " << city << endl;
  }

  cout << "\nErase Paris from the map.\n";
  city_map.erase("Paris");
  for(auto&[name, city] : city_map) {
    cout << "Key: " << name << ", Value: " << city << endl;
  }

  cout << "\nUsing CityRecord as a key in a (sorted) map requires a custom operator<().\n"; 
  map<CityRecord, uint32_t> founded_map;
  founded_map[CityRecord{"Melbourne", 500001, 2.4, 9.4}] = 1910;
  founded_map[CityRecord{"LOL-Town", 50000, 2.4, 9.4}] = 1911;
  for(auto&[name, city] : founded_map) {
    cout << "Key: " << name << ", Value: " << city << endl;
  }

  // Since our operator< is based on population, adding a record with the same 
  // population overwrites the value, but won't replace the key (!).
  cout << "\nAdd a record with a clashing key overwrites the value, but won't replace the key (!).\n";
  founded_map[CityRecord{"Berlin", 500001, 2.4, 9.4}] = 1912;
  for(auto&[name, city] : founded_map) {
    cout << "Key: " << name << ", Value: " << city << endl;
  }
  
  cout << "\nUsing an unordered map with CityRecord as a key requires an operator== and a hash function.\n";
  unordered_map<CityRecord, uint32_t> unordered_founded_map;
  unordered_founded_map[{"Melbourne", 500000, 2.4, 9.4}] = 1711;
  unordered_founded_map[{"LOL-Town", 500000, 2.4, 9.4}] = 1712;
  cout << unordered_founded_map[{"LOL-Town", 500000, 2.4, 9.4}] << endl;

  cout << "\nSince we defined the hash based only on the name, applying keys with changes to other fields still "
          "returns the value.\n";
  cout << unordered_founded_map[CityRecord{"Melbourne", 500000, 2.4, 9.4}] << endl;
  cout << unordered_founded_map[CityRecord{"Melbourne", 123456, 1.2, 3.5}] << endl;

  return 0;
}
