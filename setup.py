from setuptools import setup, Extension
from os import name
setup(
    name='clickpy',
    version='1.0.0',
    license='MIT',
    author='Elisha Hollander',
    author_email='just4now666666@gmail.com',
    description="A library able to control mouse for auto-clicking",
    long_description=open('README.md').read(),
    long_description_content_type="text/markdown",
    url='https://github.com/donno2048/clickpy',
    project_urls={
        'Documentation': 'https://github.com/donno2048/clickpy#readme',
        'Bug Reports': 'https://github.com/donno2048/clickpy/issues',
        'Source Code': 'https://github.com/donno2048/clickpy',
    },
    ext_modules=[Extension('clickpy', ['clickpy\\clickpy.c'], libraries = ["user32"])] if name == 'nt' else None,
    classifiers=["Environment :: Win32 (MS Windows)"],
    zip_safe = False,
    platforms='win32',
    include_package_data=True,
    py_modules=["clickpy"]
)
