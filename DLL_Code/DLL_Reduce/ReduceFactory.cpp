#include "pch.h"
#include "ReduceFactory.h"

Reduce* CreateReduce() {
	return new Reduce();
}