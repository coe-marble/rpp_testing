from setuptools import find_packages, setup

package_name = "rpp_testing"

setup(
    name=package_name,
    version="0.1.0",
    description="Python implementation of RPP testing framework",
    data_files=[
        (
            "share/ament_index/resource_index/packages",
            [f"resource/{package_name}"],
        ),
        (f"share/{package_name}", ["package.xml"]),
    ],
    packages=find_packages(include=["rpp_testing", "rpp_testing.*"]),
    package_dir={"": "."},
    include_package_data=True,
    install_requires=["setuptools"],
)
