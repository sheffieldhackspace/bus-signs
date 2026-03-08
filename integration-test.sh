#!/bin/bash

IP=${1:-"192.168.1.100"}
PORT=${2:-80}
BASE="http://$IP:$PORT"

ICON="ABgAAZmAAf+AGf+YH//4DgAwDv/wfH/+fv+uP/UEP1VU8VF39xV/MVX8PV/8cf++f/8eD/+wDgAwH//4Gf+YAf+AAZmAABgA"
ICON_W=24
ICON_H=9

pass=0
fail=0

run_test() {
  local description=$1
  local data=$2
  echo ""
  echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
  echo "TEST: $description"
  echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

  status=$(curl -s -o /dev/null -w "%{http_code}" "$BASE" --data "$data")

  if [ "$status" == "200" ]; then
    echo "HTTP: $status OK"
  else
    echo "HTTP: $status FAILED"
    ((fail++))
    return
  fi

  read -p "PASS or FAIL? [P/f]: " result
  if [ "$result" == "f" ] || [ "$result" == "F" ]; then
    echo "FAILED"
    ((fail++))
  else
    echo "PASSED"
    ((pass++))
  fi
}

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Bay Indicator Integration Test Suite"
echo "Target: $BASE"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# ── Text alignment ────────────────────────────────────────────────────────────

run_test "Text: left" '{
  "top":    { "text": "Left",   "horizontal_align": "left" },
  "bottom": { "text": "Left",   "horizontal_align": "left" }
}'

run_test "Text: center" '{
  "top":    { "text": "Center", "horizontal_align": "center" },
  "bottom": { "text": "Center", "horizontal_align": "center" }
}'

run_test "Text: right" '{
  "top":    { "text": "Right",  "horizontal_align": "right" },
  "bottom": { "text": "Right",  "horizontal_align": "right" }
}'

# ── Image alignment ───────────────────────────────────────────────────────────

run_test "Image: left" '{
  "top":    { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "left" },
  "bottom": { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "left" }
}'

run_test "Image: center" '{
  "top":    { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "center" },
  "bottom": { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "center" }
}'

run_test "Image: right" '{
  "top":    { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "right" },
  "bottom": { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "right" }
}'

# ── Scrolling ─────────────────────────────────────────────────────────────────

run_test "Scroll: horizontal" '{
  "top":    { "text": "This is a long horizontally scrolling message for Sheffield Hackspace", "speed": 50 },
  "bottom": { "text": "This is a long horizontally scrolling message for Sheffield Hackspace", "speed": 50 }
}'

run_test "Scroll: different speeds" '{
  "top":    { "text": "This is a long horizontally scrolling message for Sheffield Hackspace", "speed": 10 },
  "bottom": { "text": "This is a long horizontally scrolling message for Sheffield Hackspace", "speed": 50 }
}'

# ── Flashing ──────────────────────────────────────────────────────────────────

run_test "Flashing: both rows" '{
  "top":    { "text": "Flash!", "flashing": true },
  "bottom": { "text": "Flash!", "flashing": true }
}'

run_test "Flashing: top only" '{
  "top":    { "text": "Flash!", "flashing": true },
  "bottom": { "text": "No flash", "flashing": false }
}'

# ── Inverted ──────────────────────────────────────────────────────────────────

run_test "Inverted: both rows" '{
  "top":    { "text": "Inverted", "inverted": true },
  "bottom": { "text": "Inverted", "inverted": true }
}'

run_test "Inverted: top only" '{
  "top":    { "text": "Inverted", "inverted": true },
  "bottom": { "text": "Normal",   "inverted": false }
}'

# ── Image + text ──────────────────────────────────────────────────────────────

run_test "Image + text: left" '{
  "top":    { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "left" },
  "bottom": { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "left" }
}'

run_test "Image + text: center" '{
  "top":    { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "center" },
  "bottom": { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "center" }
}'

run_test "Image + text: right" '{
  "top":    { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "right" },
  "bottom": { "text": "Hackspace", "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "right" }
}'

# ── Independent rows ──────────────────────────────────────────────────────────

run_test "Independent rows: different text" '{
  "top":    { "text": "Sheffield", "horizontal_align": "left" },
  "bottom": { "text": "Hackspace", "horizontal_align": "right" }
}'

run_test "Independent rows: text + image" '{
  "top":    { "text": "Sheffield" },
  "bottom": { "image": "'"$ICON"'", "image_width": '"$ICON_W"', "image_height": '"$ICON_H"', "horizontal_align": "center" }
}'

# ── Clear display ─────────────────────────────────────────────────────────────

run_test "Clear display" '{
  "top":    { "text": "", "image": "" },
  "bottom": { "text": "", "image": "" }
}'

# ── Summary ───────────────────────────────────────────────────────────────────

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Results: $pass passed, $fail failed"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
