"""Compare generator output against committed golden files."""

from __future__ import annotations

import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GOLDENS_DIR = ROOT / "tests" / "goldens"


def golden_path(*parts: str) -> Path:
    return GOLDENS_DIR.joinpath(*parts)


def update_goldens_enabled() -> bool:
    return os.environ.get("UPDATE_GOLDENS", "").strip() in ("1", "true", "yes")


def assert_matches_golden(actual: str, relative_path: str) -> None:
    path = golden_path(relative_path)
    normalized = actual if actual.endswith("\n") else actual + "\n"
    if update_goldens_enabled():
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(normalized)
        return
    if not path.is_file():
        raise AssertionError(f"missing golden file: {path} (run make update-goldens)")
    expected = path.read_text()
    if normalized != expected:
        raise AssertionError(
            f"golden mismatch for {relative_path}\n"
            f"run make update-goldens to refresh committed output"
        )


def write_golden(actual: str, relative_path: str) -> None:
    path = golden_path(relative_path)
    path.parent.mkdir(parents=True, exist_ok=True)
    normalized = actual if actual.endswith("\n") else actual + "\n"
    path.write_text(normalized)
