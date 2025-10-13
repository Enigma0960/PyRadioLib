import gc
from contextlib import contextmanager
from time import perf_counter


@contextmanager
def assert_duration_lt(
        seconds: float,
        *,
        abs_tol: float = 0.0,  # абсолютный допуск, сек
        rel_tol: float = 0.02,  # относительный допуск (доля: 0.10 == +10%)
        disable_gc: bool = True
):
    """
    Проверяет, что блок выполняется быстрее порога seconds с допустимым
    отклонением (abs_tol и/или rel_tol). Использует perf_counter().

    Пример:
        with assert_duration_lt(0.050, rel_tol=0.10):  # +10% к порогу
            your_method()
    """
    if seconds < 0:
        raise ValueError("seconds must be >= 0")
    if abs_tol < 0 or rel_tol < 0:
        raise ValueError("abs_tol/rel_tol must be >= 0")

    effective_limit = seconds + max(abs_tol, seconds * rel_tol)

    gc_was_enabled = gc.isenabled()
    if disable_gc and gc_was_enabled:
        gc.disable()
    try:
        t0 = perf_counter()
        yield
        dt = perf_counter() - t0
    finally:
        if disable_gc and gc_was_enabled:
            gc.enable()

    if dt > effective_limit:
        msg = (
            f"Выполняется {dt:.6f}s, порог {seconds:.6f}s, "
            f"допуск abs={abs_tol:.6f}s, rel={rel_tol:.2%} "
            f"(эффективный порог {effective_limit:.6f}s)"
        )
        raise AssertionError(msg)
