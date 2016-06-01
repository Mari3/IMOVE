
#include <gtest/gtest.h>
#include <vector>

#include "../../../src/ImageProcessing/Identifier/PeopleIdentifier.h"

TEST (PeopleIdentifierTests, getClosestOneTest) {
  std::vector<Person> test_person;
  test_person.push_back(Person(Vector2(10,10), None));
  PeopleIdentifier identifier = PeopleIdentifier(test_person, 216, 384, 7.68);

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
  PeopleIdentifier identifier = PeopleIdentifier(test_people, 216, 384, 7.68);

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
  PeopleIdentifier identifier = PeopleIdentifier(test_person, 216, 384, 7.68);

  std::vector<Vector2> test_locations;
  test_locations.push_back(Vector2(200,200));
  test_locations.push_back(Vector2(50,150));
  test_locations.push_back(Vector2(60,46));

  ASSERT_EQ(identifier.getClosest(0, test_locations), -1);
}

TEST (PeopleIdentifierTests, newPersonTest) {
  std::vector<Vector2> new_locations;
  new_locations.push_back(Vector2(20,20));

  PeopleIdentifier identifier = PeopleIdentifier(216, 384, 7.68);
  std::vector<Person> identified_people = identifier.match(new_locations);

  ASSERT_EQ(identified_people.size(), (unsigned int) 1);
  ASSERT_EQ(identified_people[0].getLocation().x, 20);
}

TEST (PeopleIdentifierTests, deletePersonTest) {
  std::vector<Vector2> new_locations;
  new_locations.push_back(Vector2(20,20));
  new_locations.push_back(Vector2(400,400));

  std::vector<Person> test_people;
  test_people.push_back(Person(Vector2(20, 200), None));
  test_people.push_back(Person(Vector2(10, 10), None));

  PeopleIdentifier identifier = PeopleIdentifier(test_people, 216, 384, 7.68);
  std::vector<Person> matched_people = identifier.match(new_locations);

  ASSERT_EQ(matched_people.size(), (unsigned int) 2);
  ASSERT_EQ(matched_people[0].getLocation().y, 20);
  ASSERT_EQ(matched_people[1].getLocation().x, 400);
}

TEST (PeopleIdentifierTests, matchMultipleTest) {
  std::vector<Vector2> test_locations;
  test_locations.push_back(Vector2(20, 20));
  test_locations.push_back(Vector2(87, 400));
  test_locations.push_back(Vector2(56, 48));

  std::vector<Person> test_people;
  test_people.push_back(Person(Vector2(15, 12), None));
  test_people.push_back(Person(Vector2(60, 55), None));
  test_people.push_back(Person(Vector2(80, 403), None));

  PeopleIdentifier identifier = PeopleIdentifier(test_people, 216, 384, 7.68);
  std::vector<Person> matched_people = identifier.match(test_locations);

  ASSERT_EQ(matched_people.size(), (unsigned int) 3);
  ASSERT_EQ(matched_people[0].getLocation(), Vector2(20, 20));
  ASSERT_EQ(matched_people[1].getLocation(), Vector2(56, 48));
  ASSERT_EQ(matched_people[2].getLocation(), Vector2(87, 400));
}
