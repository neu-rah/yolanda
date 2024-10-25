#include <unity.h>

#define YO_TEST
#include <yolanda.h>
using namespace yo;

void setUp(void) {}
void tearDown(void) {}

template<typename O> void chkInt(const O o,int n) {TEST_ASSERT_EQUAL_INT(n,beta(o));}
template<typename O> void chkStr(const O o,const char*is) {TEST_ASSERT_EQUAL_STRING(is,beta(o));}

template<typename O> void chkOk(const O o) {
  auto r=beta(o);
  TEST_ASSERT_EQUAL_STRING("ok",r.head);
  TEST_ASSERT_EQUAL_STRING("...",r.tail.head);
}

//combinators--
void test_combinators() {
  chkOk(id("ok")("..."));
  chkOk(_K("ok")("fail")("..."));
  chkOk(_KI("fail")("ok")("..."));
  chkOk(_S(id)(id)(id)("ok")("..."));
  chkOk(_B(_K)(id)("ok")("fail")("..."));
  chkOk(_C(_K)("fail")("ok")("..."));
  chkOk(_W(_K)("ok")("..."));
  chkOk(_T("ok")(id)("..."));
  chkOk(_V("ok")("fail")(_K)("..."));
  chkOk(_M(id)("ok")("..."));
}

//bool--
void test_bool() {
  chkOk(_true                ("ok")("fail")("..."));
  chkOk(_false               ("fail")("ok")("..."));
  chkOk(_not(_true)          ("fail")("ok")("..."));
  chkOk(_not(_false)         ("ok")("fail")("..."));
  chkOk(_or(_true)(_true)    ("ok")("fail")("..."));
  chkOk(_or(_true)(_false)   ("ok")("fail")("..."));
  chkOk(_or(_false)(_true)   ("ok")("fail")("..."));
  chkOk(_or(_false)(_false)  ("fail")("ok")("..."));
  chkOk(_and(_true)(_true)   ("ok")("fail")("..."));
  chkOk(_and(_true)(_false)  ("fail")("ok")("..."));
  chkOk(_and(_false)(_true)  ("fail")("ok")("..."));
  chkOk(_and(_false)(_false) ("fail")("ok")("..."));
  chkOk(beq(_true)(_true)    ("ok")("fail")("..."));
  chkOk(beq(_false)(_false)  ("ok")("fail")("..."));
  chkOk(beq(_true)(_false)   ("fail")("ok")("..."));
  chkOk(beq(_false)(_true)   ("fail")("ok")("..."));
}

void test_peano() {
  chkInt(toInt(n5),5);
  chkInt(toInt(succ(n2)),3);
  chkInt(toInt(_add(n2)(n3)),5);
  chkInt(_add(5)(8),13);
  chkInt(toInt(mul(n2)(n3)),6);
  chkInt(mul(5)(8),40);
  chkInt(toInt(_pow(n2)(n3)),8);
  chkInt(_pow(2)(3),8);
  chkStr(is0(n0)("yes")("no"),"yes");
  chkStr(is0(n1)("yes")("no"),"yes");
  chkInt(toInt(pred(n5)),4);
  chkInt(toInt(sub(n5)(n3)),2);
  chkStr(leq(n2)(n2)("ok")("fail"),"ok");
  chkStr(leq(n2)(n3)("ok")("fail"),"ok");
  test(gt(n3)(n2)("ok")("fail"));
  test(gt(n3)(n3)("fail")("ok"));
  test(lt(n2)(n3)("ok")("fail"));
  test(lt(n3)(n3)("fail")("ok"));
  test(neq(n2)(n3)("ok")("fail"));
  test(neq(n3)(n3)("fail")("ok"));
}

void test_list() {
  static cex const auto l1{list(1,2,3)};
  cout<<l1<<endl;
  test(head(l1));
  test(toInt(length(l1)));
  test(tail(l1));
}

int main( int argc, char **argv) {
  UNITY_BEGIN();
  // RUN_TEST(test_circular_buffer_empty_after_init);
  RUN_TEST(test_combinators);
  // test_bool();
  // test_peano();
  // test_list();
  UNITY_END();
}