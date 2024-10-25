

# version 0.2

## test 1
### &

```text
just id(id) with value pass
RAM:   [=         ]   9.0% (used 185 bytes from 2048 bytes)
Flash: [          ]   3.6% (used 1118 bytes from 30720 bytes)
```

## test 2

```c++
cout<<id(id)<<endl;
cout<<id(id).beta()<<endl;
cout<<_true(1)(0).beta()<<endl;
cout<<_false(1)(0).beta()<<endl;
```
### &&
```text
RAM:   [=         ]   9.0% (used 185 bytes from 2048 bytes)
Flash: [          ]   5.0% (used 1522 bytes from 30720 bytes)
```

### values

```text
RAM:   [=         ]   9.0% (used 185 bytes from 2048 bytes)
Flash: [          ]   5.0% (used 1522 bytes from 30720 bytes)
```

### &

```text
RAM:   [=         ]   9.0% (used 185 bytes from 2048 bytes)
Flash: [          ]   5.0% (used 1522 bytes from 30720 bytes)
```

## test 3
```c++
cout<<id(id)<<endl;
cout<<id(id)<<endl;
cout<<_true(1)(0)<<endl;
cout<<_false(1)(0)<<endl;
```
### &&
```text
RAM:   [=         ]   9.6% (used 197 bytes from 2048 bytes)
Flash: [=         ]   5.4% (used 1666 bytes from 30720 bytes)
```
### values
```text
RAM:   [=         ]   9.6% (used 197 bytes from 2048 bytes)
Flash: [=         ]   5.4% (used 1666 bytes from 30720 bytes)
```

### &

```text
RAM:   [=         ]   9.6% (used 197 bytes from 2048 bytes)
Flash: [=         ]   5.4% (used 1666 bytes from 30720 bytes)
```
