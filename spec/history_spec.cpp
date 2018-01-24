#define TESTING
#include <gtest/gtest.h>

#include <history.c>

TEST(History, CanBeCreated){
    history * hist = create_history(10);
    EXPECT_EQ(10, hist->capacity);
    EXPECT_EQ(0, hist->size);
    EXPECT_EQ(1, hist->event_number);
    destroy_history(&hist);
}

TEST(History, CanBeDestroyed){
    history * hist = create_history(10);
    destroy_history(&hist);
    EXPECT_EQ(NULL, hist); 
}

TEST(History, CanAddEvents){
    history * hist = create_history(10);
    char * event1 = "event 1";
    char * event2 = "event 2";
    add_event(hist, event1, 64);
    add_event(hist, event2, 64);

    event1 = "Changed"; //Check deep copy

    EXPECT_EQ(2, hist->size);
    EXPECT_EQ(3, hist->event_number);
    ASSERT_STREQ("event 1", hist->events[0]);
    ASSERT_STREQ("event 2", hist->events[1]);
    destroy_history(&hist);
}

TEST(History, CanAddMoreEventsThanItsCapacity){
    history * hist = create_history(2);
    char * event1 = "event 1";
    char * event2 = "event 2";
    char * event3 = "event 3";

    add_event(hist, event1, 64);
    EXPECT_EQ(hist->head, 1);
    add_event(hist, event2, 64);
    EXPECT_EQ(hist->head, 0);
    add_event(hist, event3, 64);
    EXPECT_EQ(hist->head, 1);

    ASSERT_STREQ("event 3", hist->events[0]);
    ASSERT_STREQ("event 2", hist->events[1]);
    destroy_history(&hist);
}

TEST(HistoryCapacity, CanIncreaseWhenOldSizeIsGreaterThanOldCapacity){
    history * hist = create_history(3);
    char * event1 = "event 1";
    char * event2 = "event 2";
    char * event3 = "event 3";
    char * event4 = "event 4";

    add_event(hist, event1, 64);
    add_event(hist, event2, 64);
    add_event(hist, event3, 64);
    add_event(hist, event4, 64);

    increase_capacity(&(hist), 10); 

    EXPECT_EQ(hist->capacity, 10);
    EXPECT_EQ(hist->head, 3);
    EXPECT_EQ(hist->size, 3);
    EXPECT_EQ(hist->event_number, 5);
    ASSERT_STREQ("event 4", hist->events[2]);
    ASSERT_STREQ("event 2", hist->events[0]);
    destroy_history(&hist);
}

TEST(HistoryCapacity, CanIncreaseWhenOldSizeIsLessThanOldCapacity){
    history * hist = create_history(3);
    char * event1 = "event 1";
    char * event2 = "event 2";

    add_event(hist, event1, 64);
    add_event(hist, event2, 64);

    increase_capacity(&(hist), 5); 

    EXPECT_EQ(hist->capacity, 5);
    EXPECT_EQ(hist->head, 2);
    EXPECT_EQ(hist->size, 2);
    EXPECT_EQ(hist->event_number, 3);
    ASSERT_STREQ("event 1", hist->events[0]);
    ASSERT_STREQ("event 2", hist->events[1]);
    destroy_history(&hist);
}

TEST(HistoryCapacity, CanDecreaseWhenNewCapacityIsGreaterThanOldSize){
    history * hist = create_history(10);
    char * event1 = "event 1";
    char * event2 = "event 2";
    char * event3 = "event 3";
    char * event4 = "event 4";

    add_event(hist, event1, 64);
    add_event(hist, event2, 64);
    add_event(hist, event3, 64);
    add_event(hist, event4, 64);

    decrease_capacity(&(hist), 8); 

    EXPECT_EQ(hist->capacity, 8);
    EXPECT_EQ(hist->head, 4);
    EXPECT_EQ(hist->size, 4);
    EXPECT_EQ(hist->event_number, 5);
    ASSERT_STREQ("event 1", hist->events[0]);
    ASSERT_STREQ("event 4", hist->events[3]);
    destroy_history(&hist);
}

TEST(HistoryCapacity, CanDecreaseWhenNewCapacityIsLessThanOldSize){
    history * hist = create_history(4);
    char * event1 = "event 1";
    char * event2 = "event 2";
    char * event3 = "event 3";
    char * event4 = "event 4";

    add_event(hist, event1, 64);
    add_event(hist, event2, 64);
    add_event(hist, event3, 64);
    add_event(hist, event4, 64);

    decrease_capacity(&(hist), 2); 

    EXPECT_EQ(hist->capacity, 2);
    EXPECT_EQ(hist->head, 0);
    EXPECT_EQ(hist->size, 2);
    EXPECT_EQ(hist->event_number, 5);
    ASSERT_STREQ("event 3", hist->events[0]);
    ASSERT_STREQ("event 4", hist->events[1]);
    destroy_history(&hist);
}

TEST(HistoryCapacity, CanDecreaseWhenNewCapacityIsEqualToOldSize){
    history * hist = create_history(10);
    char * event1 = "event 1";
    char * event2 = "event 2";
    char * event3 = "event 3";
    char * event4 = "event 4";

    add_event(hist, event1, 64);
    add_event(hist, event2, 64);
    add_event(hist, event3, 64);
    add_event(hist, event4, 64);

    decrease_capacity(&(hist), 4); 

    EXPECT_EQ(hist->capacity, 4);
    EXPECT_EQ(hist->head, 0);
    EXPECT_EQ(hist->size, 4);
    EXPECT_EQ(hist->event_number, 5);
    ASSERT_STREQ("event 1", hist->events[0]);
    ASSERT_STREQ("event 4", hist->events[3]);
    destroy_history(&hist);
}


