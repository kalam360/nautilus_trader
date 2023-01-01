/* Generated with cbindgen:0.24.3 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdint.h>
#include <Python.h>

typedef enum ComponentState {
    PRE_INITIALIZED = 0,
    READY = 1,
    STARTING = 2,
    RUNNING = 3,
    STOPPING = 4,
    STOPPED = 5,
    RESUMING = 6,
    RESETTING = 7,
    DISPOSING = 8,
    DISPOSED = 9,
    DEGRADING = 10,
    DEGRADED = 11,
    FAULTING = 12,
    FAULTED = 13,
} ComponentState;

typedef enum ComponentTrigger {
    INITIALIZE = 1,
    START = 2,
    START_COMPLETED = 3,
    STOP = 4,
    STOP_COMPLETED = 5,
    RESUME = 6,
    RESUME_COMPLETED = 7,
    RESET = 8,
    RESET_COMPLETED = 9,
    DISPOSE = 10,
    DISPOSE_COMPLETED = 11,
    DEGRADE = 12,
    DEGRADE_COMPLETED = 13,
    FAULT = 14,
    FAULT_COMPLETED = 15,
} ComponentTrigger;

typedef enum LogColor {
    NORMAL = 0,
    GREEN = 1,
    BLUE = 2,
    MAGENTA = 3,
    CYAN = 4,
    YELLOW = 5,
    RED = 6,
} LogColor;

typedef enum LogLevel {
    DEBUG = 10,
    INFO = 20,
    WARNING = 30,
    ERROR = 40,
    CRITICAL = 50,
} LogLevel;

typedef struct Logger_t Logger_t;

typedef struct Rc_String Rc_String;

typedef struct TestClock TestClock;

typedef struct CTestClock {
    struct TestClock *_0;
} CTestClock;

/**
 * Represents a time event occurring at the event timestamp.
 */
typedef struct TimeEvent_t {
    /**
     * The event name.
     */
    struct Rc_String *name;
    /**
     * The event ID.
     */
    MessageCategory category;
    /**
     * The UNIX timestamp (nanoseconds) when the time event occurred.
     */
    UUID4_t event_id;
    /**
     * The message category
     */
    uint64_t ts_event;
    /**
     * The UNIX timestamp (nanoseconds) when the object was initialized.
     */
    uint64_t ts_init;
} TimeEvent_t;

typedef struct Vec_TimeEvent {
    const struct TimeEvent_t *ptr;
    uintptr_t len;
} Vec_TimeEvent;

/**
 * Logger is not C FFI safe, so we box and pass it as an opaque pointer.
 * This works because Logger fields don't need to be accessed, only functions
 * are called.
 */
typedef struct CLogger {
    struct Logger_t *_0;
} CLogger;

struct CTestClock test_clock_new(void);

void test_clock_free(struct CTestClock clock);

void test_clock_set_time(struct CTestClock *clock, uint64_t to_time_ns);

uint64_t test_clock_time_ns(const struct CTestClock *clock);

PyObject *test_clock_timer_names(const struct CTestClock *clock);

uintptr_t test_clock_timer_count(struct CTestClock *clock);

/**
 * # Safety
 * - Assumes `name_ptr` is a valid C string pointer.
 */
void test_clock_set_time_alert_ns(struct CTestClock *clock,
                                  const char *name_ptr,
                                  uint64_t alert_time_ns);

/**
 * # Safety
 * - Assumes `name_ptr` is a valid C string pointer.
 */
void test_clock_set_timer_ns(struct CTestClock *clock,
                             const char *name_ptr,
                             uint64_t interval_ns,
                             uint64_t start_time_ns,
                             uint64_t stop_time_ns);

/**
 * # Safety
 * - Assumes `set_time` is a correct `uint8_t` of either 0 or 1.
 */
struct Vec_TimeEvent test_clock_advance_time(struct CTestClock *clock,
                                             uint64_t to_time_ns,
                                             uint8_t set_time);

void vec_time_events_drop(struct Vec_TimeEvent v);

/**
 * # Safety
 * - Assumes `name_ptr` is a valid C string pointer.
 */
uint64_t test_clock_next_time_ns(struct CTestClock *clock, const char *name_ptr);

/**
 * # Safety
 * - Assumes `name_ptr` is a valid C string pointer.
 */
void test_clock_cancel_timer(struct CTestClock *clock, const char *name_ptr);

void test_clock_cancel_timers(struct CTestClock *clock);

const char *component_state_to_cstr(enum ComponentState value);

/**
 * Returns an enum from a Python string.
 *
 * # Safety
 * - Assumes `ptr` is a valid C string pointer.
 */
enum ComponentState component_state_from_cstr(const char *ptr);

const char *component_trigger_to_cstr(enum ComponentTrigger value);

/**
 * Returns an enum from a Python string.
 *
 * # Safety
 * - Assumes `ptr` is a valid C string pointer.
 */
enum ComponentTrigger component_trigger_from_cstr(const char *ptr);

const char *log_level_to_cstr(enum LogLevel value);

/**
 * Returns an enum from a Python string.
 *
 * # Safety
 * - Assumes `ptr` is a valid C string pointer.
 */
enum LogLevel log_level_from_cstr(const char *ptr);

const char *log_color_to_cstr(enum LogColor value);

/**
 * Returns an enum from a Python string.
 *
 * # Safety
 * - Assumes `ptr` is a valid C string pointer.
 */
enum LogColor log_color_from_cstr(const char *ptr);

/**
 * Creates a new logger.
 *
 * # Safety
 * - Assumes `trader_id_ptr` is a valid C string pointer.
 * - Assumes `machine_id_ptr` is a valid C string pointer.
 * - Assumes `instance_id_ptr` is a valid C string pointer.
 */
struct CLogger logger_new(PyObject *trader_id_ptr,
                          PyObject *machine_id_ptr,
                          PyObject *instance_id_ptr,
                          enum LogLevel level_stdout,
                          uint8_t is_bypassed);

void logger_free(struct CLogger logger);

void flush(struct CLogger *logger);

const char *logger_get_trader_id_cstr(const struct CLogger *logger);

const char *logger_get_machine_id_cstr(const struct CLogger *logger);

UUID4_t logger_get_instance_id(const struct CLogger *logger);

uint8_t logger_is_bypassed(const struct CLogger *logger);

/**
 * Log a message.
 *
 * # Safety
 * - Assumes `component_ptr` is a valid C string pointer.
 * - Assumes `msg_ptr` is a valid C string pointer.
 */
void logger_log(struct CLogger *logger,
                uint64_t timestamp_ns,
                enum LogLevel level,
                enum LogColor color,
                PyObject *component_ptr,
                PyObject *msg_ptr);

/**
 * # Safety
 * - Assumes `name` is borrowed from a valid Python UTF-8 `str`.
 */
struct TimeEvent_t time_event_new(const char *name,
                                  UUID4_t event_id,
                                  uint64_t ts_event,
                                  uint64_t ts_init);

struct TimeEvent_t time_event_copy(const struct TimeEvent_t *event);

void time_event_free(struct TimeEvent_t event);

const char *time_event_name_cstr(const struct TimeEvent_t *event);
