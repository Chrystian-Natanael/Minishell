#!/bin/bash

diff <( ./test_b ) <( pwd; echo Kelly Hayd; env ) && echo SUCCESS || echo FAILED