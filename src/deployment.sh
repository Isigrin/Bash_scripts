#!/bin/bash

sshpass -p student scp -o StrictHostKeyChecking=no src/cat/s21_cat student@10.10.0.2:/usr/local/bin/s21_cat

sshpass -p student scp -o StrictHostKeyChecking=no src/grep/s21_grep student@10.10.0.2:/usr/local/bin/s21_grep
