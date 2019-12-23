//
// Created by Henry Little on 2019-09-11.
//

#include "Context.h"

Context& Context::Instance() {
    static Context(context);
    return context;
}