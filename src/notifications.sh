#!/bin/bash


TELEGRAM_BOT_TOKEN=6613118673:AAH_6IKypYzRRpdmqLbAZNiTlDUIWMy61xw
TELEGRAM_USER_ID=391329291

URL=https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage
TEXT="Project information: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG%0AStage:+$CI_JOB_STAGE%0AStatus:+$CI_JOB_STATUS"

curl -s --max-time 15 -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
