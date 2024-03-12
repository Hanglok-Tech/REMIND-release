#pragma once

#include "RemindCustomizedMessage.h"
#include "BlockingQueue.hpp"

using RemindMessageQueue = BlockingQueue<RemindCustomizedMessage*>;

