#include<main.cpp>
#include <unity.h>
#include<slave_model.c>


void step(){
    slave_model_step();
}

//init
void test_start(void){
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_init, slave_model_DW.is_c3_slave_model);  
}

void test_one(void){
    slave_model_U.msg=1;
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_addrValidation, slave_model_DW.is_c3_slave_model);  
}

void test_two(void){
    slave_model_U.thisAddr=10;
    slave_model_U.msg=10;
    slave_model_U.report=2;
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_sendReport, slave_model_DW.is_c3_slave_model);  
    TEST_ASSERT_EQUAL(2.0, slave_model_Y.dataBus);
}

void test_three(void){
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_getMsg, slave_model_DW.is_c3_slave_model);  
    TEST_ASSERT_EQUAL(1.0, slave_model_Y.modeBus);
}
void test_four(void){
    slave_model_U.msg=2;
    slave_model_U.report=3;
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_sendReport, slave_model_DW.is_c3_slave_model);  
    TEST_ASSERT_EQUAL(0.0, slave_model_Y.modeBus);
    TEST_ASSERT_EQUAL(3.0, slave_model_Y.dataBus);
}

void test_five(void){
    slave_model_U.msg=0;
    step();
    TEST_ASSERT_EQUAL(slave_model_IN_init, slave_model_DW.is_c3_slave_model);  
}

int main(int argc, char **argv){

    slave_model_initialize();

    UNITY_BEGIN();
    RUN_TEST(test_start); // init
    RUN_TEST(test_one); // init
    RUN_TEST(test_two); // init
    RUN_TEST(test_three); // init
    RUN_TEST(test_four); // init
    RUN_TEST(test_five); // init
    UNITY_END();

    return 0;
}

