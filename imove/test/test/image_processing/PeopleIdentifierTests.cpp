
#include <gtest/gtest.h>
#include <vector>

#include "../../../src/image_processing/identifier/PeopleIdentifier.h"

TEST (PeopleIdentifierTests, getClosestOneTest) {
  std::vector<Person> test_person;
  test_person.push_back(Person(Vector2(10,10), None));
  PeopleIdentifier identifier = PeopleIdentifier(test_person);

  std::vector<Vector2> test_locations;
  test_locations.push_back(Vector2(20,20));
  test_locations.push_back(Vector2(10,15));
  test_locations.push_back(Vector2(11,16));

  ASSERT_EQ(identifier.getClosest(0, test_locations), 1);
}

TEST (PeopleIdentifierTests, getClosestMultipleTest) {
  std::vector<Person> test_people;
  test_people.push_back(Person(Vector2(10,10), None));
  test_people.push_back(Person(Vector2(30,30), None));
  PeopleIdentifier identifier = PeopleIdentifier(test_people);

  std::vector<Vector2> test_locations;
  test_locations.push_back(Vector2(20,20));
  test_locations.push_back(Vector2(10,15));
  test_locations.push_back(Vector2(11,16));

  ASSERT_EQ(identifier.getClosest(0, test_locations), 1);
  ASSERT_EQ(identifier.getClosest(1, test_locations), 0);
}

TEST (PeopleIdentifierTests, getClosestNoneTest) {
  std::vector<Person> test_person;
  test_person.push_back(Person(Vector2(10,10), None));
  PeopleIdentifier identifier = PeopleIdentifier(test_person);

  std::vector<Vector2> test_locations;
  test_locations.push_back(Vector2(200,200));
  test_locations.push_back(Vector2(50,150));
  test_locations.push_back(Vector2(60,46));

  ASSERT_EQ(identifier.getClosest(0, test_locations), -1);
}

TEST (PeopleIdentifierTests, identifyOne) {

}
