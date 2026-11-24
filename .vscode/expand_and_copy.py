import argparse
import base64
import subprocess
import sys
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--expander", type=Path, required=True)
    parser.add_argument("--lib", type=Path, required=True)
    parser.add_argument("--origname", required=True)
    parser.add_argument("source", type=Path)
    args = parser.parse_args()

    result = subprocess.run(
        [
            sys.executable,
            str(args.expander),
            "--lib",
            str(args.lib),
            "--origname",
            args.origname,
            str(args.source),
        ],
        check=False,
    )
    if result.returncode != 0:
        return result.returncode

    output = Path("combined.cpp")
    try:
        data = output.read_bytes()
    except OSError as error:
        print(f"Failed to read {output}: {error}", file=sys.stderr)
        return 1

    encoded = base64.b64encode(data).decode("ascii")
    sys.stdout.write(f"\x1b]52;c;{encoded}\x07")
    sys.stdout.flush()
    print(f"Expanded and copied {output} ({len(data):,} bytes) to the clipboard.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
