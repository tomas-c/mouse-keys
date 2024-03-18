#include <ApplicationServices/ApplicationServices.h>
#include <time.h>

double diff_timespec(const struct timespec *time1, const struct timespec *time0) {
    return (time1->tv_sec - time0->tv_sec) + (time1->tv_nsec - time0->tv_nsec) / 1000000000.0;
}

double max(double x, double y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

double min(double x, double y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

CGEventFlags lastFlags = 0;

bool l1_pressed = false;
struct timespec l1_pressed_at;

bool r1_pressed = false;
struct timespec r1_pressed_at;

bool u1_pressed = false;
struct timespec u1_pressed_at;

bool d1_pressed = false;
struct timespec d1_pressed_at;

bool l2_pressed = false;
struct timespec l2_pressed_at;

bool r2_pressed = false;
struct timespec r2_pressed_at;

bool u2_pressed = false;
struct timespec u2_pressed_at;

bool d2_pressed = false;
struct timespec d2_pressed_at;

bool left_mouse_down = false;

// The following callback method is invoked on every keypress.
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    // Need to keep track of whether mouse button is pressed so that we could ensure dragging works with our fake mouse
    if (type == kCGEventLeftMouseDown) {
        left_mouse_down = true;
        return event;
    }
    if (type == kCGEventLeftMouseUp) {
        left_mouse_down = false;
        return event;
    }

    if (type != kCGEventKeyDown && type != kCGEventKeyUp && type != kCGEventFlagsChanged) {
        return event;
    }

    CGEventFlags flags = CGEventGetFlags(event);

    // Retrieve the incoming keycode.
    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    // Calculate key up/down.
    bool down = false;
    if (type == kCGEventFlagsChanged) {
        switch (keyCode) {
            case 54:  // [right-cmd]
            case 55:  // [left-cmd]
                down = (flags & kCGEventFlagMaskCommand) &&
                       !(lastFlags & kCGEventFlagMaskCommand);
                break;
            case 56:  // [left-shift]
            case 60:  // [right-shift]
                down = (flags & kCGEventFlagMaskShift) &&
                       !(lastFlags & kCGEventFlagMaskShift);
                break;
            case 58:  // [left-option]
            case 61:  // [right-option]
                down = (flags & kCGEventFlagMaskAlternate) &&
                       !(lastFlags & kCGEventFlagMaskAlternate);
                break;
            case 59:  // [left-ctrl]
            case 62:  // [right-ctrl]
                down = (flags & kCGEventFlagMaskControl) &&
                       !(lastFlags & kCGEventFlagMaskControl);
                break;
            case 57:  // [caps]
                down = (flags & kCGEventFlagMaskAlphaShift) &&
                       !(lastFlags & kCGEventFlagMaskAlphaShift);
                break;
            default:
                break;
        }
    } else if (type == kCGEventKeyDown) {
        down = true;
    }
    lastFlags = flags;

    if (keyCode == 105) {  // F13
        if (down) {
            if (!l1_pressed) {
                printf("l1 pressed\n");
                l1_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &l1_pressed_at);
            }
        } else {
            if (l1_pressed) {
                printf("l1 released\n");
                l1_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 113) {  // F15
        if (down) {
            if (!r1_pressed) {
                printf("r1 pressed\n");
                r1_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &r1_pressed_at);
            }
        } else {
            if (r1_pressed) {
                printf("r1 released\n");
                r1_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 106) {  // F16
        if (down) {
            if (!d1_pressed) {
                printf("d1 pressed\n");
                d1_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &d1_pressed_at);
            }
        } else {
            if (d1_pressed) {
                printf("d1 released\n");
                d1_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 107) {  // F14
        if (down) {
            if (!u1_pressed) {
                printf("u1 pressed\n");
                u1_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &u1_pressed_at);
            }
        } else {
            if (u1_pressed) {
                printf("u1 released\n");
                u1_pressed = false;
            }
        }
        return NULL;
    }

    if (keyCode == 64) {  // F17
        if (down) {
            if (!l2_pressed) {
                printf("l2 pressed\n");
                l2_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &l2_pressed_at);
            }
        } else {
            if (l2_pressed) {
                printf("l2 released\n");
                l2_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 90) {  // F20
        if (down) {
            if (!d2_pressed) {
                printf("d2 pressed\n");
                d2_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &d2_pressed_at);
            }
        } else {
            if (d2_pressed) {
                printf("d2 released\n");
                d2_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 80) {  // F19
        if (down) {
            if (!r2_pressed) {
                printf("r2 pressed\n");
                r2_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &r2_pressed_at);
            }
        } else {
            if (r2_pressed) {
                printf("r2 released\n");
                r2_pressed = false;
            }
        }
        return NULL;
    } else if (keyCode == 79) {  // F18
        if (down) {
            if (!u2_pressed) {
                printf("u2 pressed\n");
                u2_pressed = true;
                clock_gettime(CLOCK_MONOTONIC_RAW, &u2_pressed_at);
            }
        } else {
            if (u2_pressed) {
                printf("u2 released\n");
                u2_pressed = false;
            }
        }
        return NULL;
    }

    return event;
}

struct timespec last_loop_at;

double acceleration_period_s = 2;
double loop_period_s = 0.01;
double max_step_px_per_s = 3000;

CGPoint last_pos;

double ramp(double duration_s) {
    return max(0.0, min(1.0, duration_s / acceleration_period_s));
}

void mover_thread_run(CFRunLoopTimerRef timer, void *data) {
    if (!l1_pressed && !r1_pressed && !d1_pressed && !u1_pressed &&
        !l2_pressed && !r2_pressed && !d2_pressed && !u2_pressed) {
        return;
    }

    struct timespec curr_loop_at;
    clock_gettime(CLOCK_MONOTONIC_RAW, &curr_loop_at);

    double x_delta_px = 0;
    double y_delta_px = 0;

    if (l1_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &l1_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &l1_pressed_at));
        x_delta_px -= speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (r1_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &r1_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &r1_pressed_at));
        x_delta_px += speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (d1_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &d1_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &d1_pressed_at));
        y_delta_px += speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (u1_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &u1_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &u1_pressed_at));
        y_delta_px -= speed_factor * max_step_px_per_s * time_delta_s;
    }

    if (l2_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &l2_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &l2_pressed_at));
        x_delta_px -= speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (r2_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &r2_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &r2_pressed_at));
        x_delta_px += speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (d2_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &d2_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &d2_pressed_at));
        y_delta_px += speed_factor * max_step_px_per_s * time_delta_s;
    }
    if (u2_pressed) {
        double time_delta_s = min(diff_timespec(&curr_loop_at, &u2_pressed_at), diff_timespec(&curr_loop_at, &last_loop_at));
        double speed_factor = ramp(diff_timespec(&curr_loop_at, &u2_pressed_at));
        y_delta_px -= speed_factor * max_step_px_per_s * time_delta_s;
    }

    if (x_delta_px != 0 || y_delta_px != 0) {
        // printf("moving\n");
        CGEventRef getLocationEvent = CGEventCreate(NULL);
        CGPoint curr_pos = CGEventGetLocation(getLocationEvent);
        // printf("moving %f %f\n", x_delta_px, y_delta_px);
        CFRelease(getLocationEvent);

        CGPoint next_pos =
            CGPointMake(curr_pos.x + x_delta_px, curr_pos.y + y_delta_px);

        // Make sure cursor does not go beyond display boundaries
        CGDisplayCount display_count = 0;
        CGDirectDisplayID display_id;
        CGGetDisplaysWithPoint(next_pos, 1, &display_id, &display_count);
        if (display_count == 0) {
            // next_pos does not fit on any display, fit to the last known display
            CGGetDisplaysWithPoint(last_pos, 1, &display_id, &display_count);
            if (display_count != 0) {
                CGRect display_rect = CGDisplayBounds(display_id);
                next_pos.x = max(display_rect.origin.x, min(display_rect.origin.x + display_rect.size.width - 1, next_pos.x));
                next_pos.y = max(display_rect.origin.y, min(display_rect.origin.y + display_rect.size.height - 1, next_pos.y));
            }
        }

        CGEventType eventType;
        if (left_mouse_down) {
            eventType = kCGEventLeftMouseDragged;
        } else {
            eventType = kCGEventMouseMoved;
        }

        CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, eventType, next_pos,
                                                       kCGMouseButtonLeft  // ignored
        );
        CGEventSetDoubleValueField(moveEvent, kCGMouseEventDeltaX, next_pos.x - curr_pos.x);
        CGEventSetDoubleValueField(moveEvent, kCGMouseEventDeltaY, next_pos.y - curr_pos.y);
        CGEventPost(kCGHIDEventTap, moveEvent);
        CFRelease(moveEvent);

        last_pos = next_pos;
        last_loop_at = curr_loop_at;
    }
    return;
}

int main() {
    // Create an event tap to retrieve keypresses.
    CGEventMask eventMask = CGEventMaskBit(kCGEventLeftMouseDown) | CGEventMaskBit(kCGEventLeftMouseUp) | CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyUp) | CGEventMaskBit(kCGEventFlagsChanged);
    CFMachPortRef eventTap =
        CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask,
                         CGEventCallback, NULL);

    // Exit the program if unable to create the event tap.
    if (!eventTap) {
        fprintf(stderr, "ERROR: Unable to create event tap.\n");
        exit(1);
    }

    // Create a run loop source and add enable the event tap.
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    // Add a timer
    CFRunLoopTimerContext context = {0, NULL, NULL, NULL, NULL};
    CFRunLoopTimerRef timer = CFRunLoopTimerCreate(kCFAllocatorDefault, CFAbsoluteTimeGetCurrent() + loop_period_s, loop_period_s, 0, 0, &mover_thread_run, &context);
    CFRunLoopAddTimer(CFRunLoopGetCurrent(), timer, kCFRunLoopCommonModes);

    // Start the loop
    CFRunLoopRun();
    return 0;
}