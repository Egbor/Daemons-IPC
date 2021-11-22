#!/bin/bash

pid=$(cat /tmp/serverpid)

kill -15 $pid
