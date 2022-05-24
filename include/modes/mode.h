#pragma once

struct Mode {
    virtual void initiateMode() = 0;
    virtual void terminateMode() = 0;
    virtual void loop() = 0;
};