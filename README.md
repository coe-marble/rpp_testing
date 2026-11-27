# rpp_testing

Shared fixtures, test libraries, and mock workspaces for RPP packages.

The precompiled C++ fixture includes the allocation and `hintSize` samples used by
`rpp_cpp`. Generate it with `scripts/build_rpp_autogen.sh` before packaging
`rpp_testing`; its generated sources and wrappers are installed as package data.
Consumer test builds use that installed fixture directly.

Documentation is maintained in `rpp_docs`:

- [Testing support](../../rpp_docs/docs/testing.md).
- [Test image](../../rpp_docs/docs/test-image.md).

[Read the guide on GitHub](https://github.com/coe-marble/rpp_docs/blob/develop/docs/testing.md).
