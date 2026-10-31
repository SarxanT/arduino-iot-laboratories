#!/usr/bin/env python3
"""Static repository checks; not a substitute for compiling/uploading firmware."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
sketches = sorted(root.rglob('*.ino'))
assert len(sketches) == 6, f'Expected six sketches, got {len(sketches)}'
for sketch in sketches:
    assert sketch.stem == sketch.parent.name, f'Sketch folder mismatch: {sketch}'
    source = sketch.read_text(encoding='utf-8')
    assert 'void setup()' in source and 'void loop()' in source, sketch
    assert not re.search(r'\b(10\.21\.46\.|192\.168\.0\.177)\b', source), sketch
    assert not re.search(r'(?:sk-[A-Za-z0-9]{15,}|ghp_[A-Za-z0-9]{20,})', source), sketch
key_dir = root / 'lab-06-thingspeak-ultrasonic' / 'thingspeak_ultrasonic'
if (key_dir / 'secrets.h').exists():
    print('Notice: local secrets.h exists. Confirm Git ignores it before committing.')
example = (key_dir / 'secrets.example.h').read_text(encoding='utf-8')
assert 'REPLACE_WITH_YOUR_WRITE_KEY' in example
assert '#define SECRET_CH_ID 0UL' in example
print('Static checks passed: six sketch folders, placeholders, no known sensitive originals.')
