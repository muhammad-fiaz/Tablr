# Contributing to Tablr

Thank you for your interest in contributing to Tablr! This document provides guidelines for contributing to the project.

## Code of Conduct

Be respectful and inclusive in all interactions.

## How to Contribute

### Reporting Bugs

- Use the GitHub issue tracker
- Include a clear description and reproduction steps
- Provide system information (OS, compiler version)

### Suggesting Features

- Open an issue with the "enhancement" label
- Describe the feature and its use case
- Discuss implementation approach

### Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass (`xmake build && xmake run tests`)
6. Update documentation
7. Commit with clear messages
8. Push to your fork
9. Open a Pull Request

## Development Setup

```bash
git clone https://github.com/muhammad-fiaz/tablr.git
cd tablr
xmake build
xmake run tests
```

## Coding Standards

- Follow C11 and C++17 standards
- Use consistent indentation (4 spaces)
- Add docstrings to all functions
- Keep functions focused and modular
- Avoid compiler warnings
- Write clear, self-documenting code

## Testing

- Add unit tests for new features
- Ensure all tests pass before submitting PR
- Test on multiple platforms if possible

## Documentation

- Update API documentation for new functions
- Add usage examples
- Update README if needed

## License

By contributing, you agree that your contributions will be licensed under the Apache License 2.0.
