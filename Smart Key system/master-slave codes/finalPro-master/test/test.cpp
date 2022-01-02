#include<main.cpp>
#include <unity.h>
#include<master_model.c>


void step(){
    master_model_step();
}

//init
void test_start(void){
    step();
    TEST_ASSERT_EQUAL(master_model_IN_init, master_model_DW.is_c3_master_model);  
}

void test_one(void){
    master_model_U.deviceSelect=1;
    step();
    TEST_ASSERT_EQUAL(master_model_IN_initSend, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(1.0, master_model_Y.dataBus);
}

void test_two(void){
    master_model_U.address=10;
    step();
    TEST_ASSERT_EQUAL(master_model_IN_addressSend, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(10.0, master_model_Y.dataBus);
}

void test_three(void){
    step();
    TEST_ASSERT_EQUAL(master_model_IN_getReport, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(1.0, master_model_Y.modeBus);
}
void test_four(void){
    master_model_U.in=2;
    step();
    TEST_ASSERT_EQUAL(master_model_IN_sendMsg, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(0.0, master_model_Y.modeBus);
    TEST_ASSERT_EQUAL(2.0, master_model_Y.dataBus);
}

void test_five(void){
    master_model_U.deviceSelect=0;
    step();
    TEST_ASSERT_EQUAL(master_model_IN_getReport, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(1.0, master_model_Y.modeBus);
}

void test_six(void){
    master_model_U.deviceSelect=2;
    step();
    TEST_ASSERT_EQUAL(master_model_IN_init, master_model_DW.is_c3_master_model);  
    TEST_ASSERT_EQUAL(0.0, master_model_Y.dataBus);
}

int main(int argc, char **argv){

    master_model_initialize();

    UNITY_BEGIN();
    RUN_TEST(test_start); // init
    RUN_TEST(test_one); // init
    RUN_TEST(test_two); // init
    RUN_TEST(test_three); // init
    RUN_TEST(test_four); // init
    RUN_TEST(test_five); // init
    RUN_TEST(test_six); // init
    UNITY_END();

    return 0;
}

