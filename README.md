# rpp_testing

A python package that installs testing data for rpp.
This package is used by the other packages in a way that allows them to run tests without having to include the testing data in their own repositories. The testing data is stored in a separate repository and is installed as a package dependency.

# Description


`example_plugins` contains a set of simple testing plugin implementations. These plugins are installed in the
testing rpp system from rpp_cli/testing module. The plugins are used to test the functionality of the rpp system and to provide examples of how to implement plugins.
`complex_plugins` contains a set of more complex testing plugin implementations. They are not automatically installed in the testing rpp system, but can be used to test the functionality of the rpp system and to provide examples of how to implement plugins.
`mock_workspaces` contains a set of mock workspaces that can be used to test the functionality of the rpp system and to provide examples of how to implement workspaces.
`test_component_cpp` contains a component that implements a simple C++ plugin.
`test_component_py` contains a component that implements a simple Python plugin.
`test_libs` contains a set of testing libraries