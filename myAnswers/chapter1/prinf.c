#include <stdio.h>

void crash_investigation() {
    // __func__ and __LINE__ are magical macros injected by the compiler!
    printf("[DEBUG] Entered function %s on line %d\n", __func__, __LINE__);
}

/**
 * @brief 程序入口函数，启动并委托执行崩溃调查流程。
 *
 * 该函数仅负责调用崩溃调查逻辑并返回进程退出码。实际的诊断、日志收集或
 * 故障复现由内部的崩溃调查例程完成。
 *
 * @param 无
 * @return int 程序退出状态码；通常返回 0 表示主流程正常结束。
 * @throws 可能因崩溃调查例程内部触发异常（如断言失败、段错误、调用 abort/exit）
 *         导致进程异常终止或以非零状态码退出。
 */
int main(void) {
    crash_investigation();
    return 0;
}
