#include <gtest/gtest.h>

#define TESTING

#include <environment.c>

class TestEnvironment : public ::testing::Test{
    protected:
        void SetUp(){
            env = create_environment();
        }
        void TearDown(){
            destroy_environment(&env);
        }

        environment * env;
};

TEST_F(TestEnvironment, ThePromptIsNullTerminated){
    EXPECT_EQ('\0', env->prompt[63]);
}

TEST_F(TestEnvironment, CanSetThePrompt){
    set_prompt(env, "Sample Prompt");
    ASSERT_STREQ("Sample Prompt", env->prompt);
}
