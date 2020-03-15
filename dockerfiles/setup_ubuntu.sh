# Is the ubuntu:seqan3 image already in the docker daemon?
IID_SEQAN3="$(docker images -q ubuntu:seqan3 2> /dev/null)"

# Build the ubuntu:seqan3 docker image
docker build --iidfile iid.tmp -f ubuntu/cmake.dkr -t ubuntu:seqan3 ..

IID_SEQAN3_POST="$(cat iid.tmp)"
rm iid.tmp

# If the ubuntu:seqan3 image was pre-built
# then there would now be a dangling image
# so we will remove that old image.
if [[ "${IID_SEQAN3}" != "" ]]; then
        if [[ "${IID_SEQAN3}" != "${IID_SEQAN3_POST:7:12}" ]]; then
                docker rmi "${IID_SEQAN3}"
        fi
fi

# Is the hopa:latest image already in the docker daemon?
IID_HOPA="$(docker images -q hopa:latest 2> /dev/null)"

# Install the hopa program itself
docker build --iidfile iid.tmp -f ubuntu/install.dkr -t hopa ..

IID_HOPA_POST="$(cat iid.tmp)"
rm iid.tmp

if [[ "${IID_HOPA}" != "" ]]; then
        if [[ "${IID_HOPA}" != "${IID_HOPA_POST:7:12}" ]]; then
                docker rmi "${IID_HOPA}"
        fi
fi
