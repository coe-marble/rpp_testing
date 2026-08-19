from setuptools import find_packages, setup

setup(
    name="rpp_testing",
    version="0.1.0",
    description="Python implementation of RPP testing framework",
    packages=find_packages(include=["rpp_testing", "rpp_testing.*"]),
    package_dir={"": "."},
    include_package_data=True,
    install_requires=[],
)
